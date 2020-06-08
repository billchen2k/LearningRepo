
import Cocoa

class Shared {
    static var NUM = 3;
}


print(Shared.NUM)

Shared.NUM = 4;

print(Shared.NUM)

func fetchAllRooms(completion: @escaping ([RemoteRoom]?) -> Void) {
  guard let url = URL(string: "http://localhost:5984/rooms/_all_docs?include_docs=true") else {
    completion(nil)
    return
  }
  Alamofire.request(url,
                    method: .get,
                    parameters: ["include_docs": "true"])
  .validate()
  .responseJSON { response in
    guard response.result.isSuccess else {
      print("Error while fetching remote rooms: \(String(describing: response.result.error)")
      completion(nil)
      return
    }

    guard let value = response.result.value as? [String: Any],
      let rows = value["rows"] as? [[String: Any]] else {
        print("Malformed data received from fetchAllRooms service")
        completion(nil)
        return
    }

    let rooms = rows.flatMap { roomDict in return RemoteRoom(jsonData: roomDict) }
    completion(rooms)
  }
}
